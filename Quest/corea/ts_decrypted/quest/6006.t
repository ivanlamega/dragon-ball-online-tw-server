CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6006;
	title = 600602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 600607;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3031101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6005;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 600609;
				ctype = 1;
				idx = 3031101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 600608;
				gtype = 1;
				area = 600601;
				goal = 600604;
				grade = -1;
				rwd = 100;
				sort = 600605;
				stype = 8;
				taid = 1;
				title = 600602;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 600608;
			gtype = 1;
			oklnk = 2;
			area = 600601;
			goal = 600604;
			sort = 600605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 600602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 600614;
			nextlnk = 253;
			rwdtbl = 600601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181101;
			}
		}
	}
}

