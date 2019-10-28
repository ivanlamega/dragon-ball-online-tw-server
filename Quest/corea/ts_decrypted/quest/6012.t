CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6012;
	title = 601202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 601207;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3181101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6006;";
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 601209;
				ctype = 1;
				idx = 3181101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 601208;
				gtype = 1;
				area = 601201;
				goal = 601204;
				grade = -1;
				rwd = 100;
				sort = 601205;
				stype = 8;
				taid = 1;
				title = 601202;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 601208;
			gtype = 1;
			oklnk = 2;
			area = 601201;
			goal = 601204;
			sort = 601205;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 601202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 601214;
			nextlnk = 253;
			rwdtbl = 601201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7091107;
			}
		}
	}
}

