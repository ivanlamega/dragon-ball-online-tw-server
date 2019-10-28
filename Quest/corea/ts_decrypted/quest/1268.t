CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1268;
	title = 126802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 126809;
				ctype = 1;
				idx = 4261104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 126808;
				gtype = 1;
				area = 126801;
				goal = 126804;
				grade = 132203;
				rwd = 100;
				sort = 126805;
				stype = 1;
				taid = 1;
				title = 126802;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 126814;
			nextlnk = 254;
			rwdtbl = 126801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickObject
			{
				objidx = "842;";
				widx = 1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 126808;
			gtype = 1;
			oklnk = 2;
			area = 126801;
			goal = 126804;
			sort = 126805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 126802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 126807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4261104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1267;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

