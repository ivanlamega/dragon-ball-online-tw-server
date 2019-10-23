CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1378;
	title = 137802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 137808;
				gtype = 1;
				area = 137801;
				goal = 137804;
				grade = 132203;
				rwd = 100;
				sort = 137805;
				stype = 1;
				taid = 1;
				title = 137802;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 137814;
			nextlnk = 254;
			rwdtbl = 137801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131122;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 137808;
			gtype = 1;
			oklnk = 2;
			area = 137801;
			goal = 137804;
			sort = 137805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 137802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 137807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSClickObject
			{
				objidx = "696;";
				widx = 1;
			}
			CDboTSCheckClrQst
			{
				and = "1377;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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

