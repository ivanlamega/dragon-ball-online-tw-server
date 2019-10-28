CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 127;
	title = 12702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 12709;
				ctype = 1;
				idx = 4071110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 12708;
				gtype = 1;
				area = 12701;
				goal = 12704;
				grade = 132203;
				rwd = 100;
				sort = 12705;
				stype = 1;
				taid = 1;
				title = 12702;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 12714;
			nextlnk = 254;
			rwdtbl = 12701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2801201;
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
			cont = 12708;
			gtype = 1;
			oklnk = 2;
			area = 12701;
			goal = 12704;
			sort = 12705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 12702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 12707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 4071110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 25;
				minlvl = 17;
			}
			CDboTSCheckClrQst
			{
				and = "126;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

