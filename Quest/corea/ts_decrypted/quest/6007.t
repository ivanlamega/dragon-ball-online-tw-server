CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6007;
	title = 600702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 600709;
				ctype = 1;
				idx = 3031101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 600708;
				gtype = 1;
				area = 600701;
				goal = 600704;
				grade = -1;
				rwd = 100;
				sort = 600705;
				stype = 8;
				taid = 1;
				title = 600702;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 600707;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 600714;
			nextlnk = 253;
			rwdtbl = 600701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3221201;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 600708;
			gtype = 1;
			oklnk = 2;
			area = 600701;
			goal = 600704;
			sort = 600705;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 600702;
		}
	}
}

