CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6038;
	title = 603802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 603808;
			gtype = 1;
			oklnk = 2;
			area = 603801;
			goal = 603804;
			sort = 603805;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 603802;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 603814;
			nextlnk = 253;
			rwdtbl = 603801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3611101;
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
				conv = 603809;
				ctype = 1;
				idx = 4372203;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 603808;
				gtype = 1;
				area = 603801;
				goal = 603804;
				grade = -1;
				rwd = 100;
				sort = 603805;
				stype = 8;
				taid = 1;
				title = 603802;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
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
			stdiag = 603807;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
			CDboTSClickNPC
			{
				npcidx = 4372203;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6037;";
			}
		}
	}
}

