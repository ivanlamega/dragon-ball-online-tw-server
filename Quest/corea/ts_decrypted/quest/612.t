CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 612;
	title = 61202;

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
				conv = 61209;
				ctype = 1;
				idx = 3173103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 61208;
				gtype = 1;
				area = 61201;
				goal = 61204;
				grade = 132203;
				rwd = 100;
				sort = 61205;
				stype = 2;
				taid = 1;
				title = 61202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 61207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3173103;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "611;";
			}
		}
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 61208;
			gtype = 1;
			oklnk = 2;
			area = 61201;
			goal = 61204;
			sort = 61205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 61202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 61214;
			nextlnk = 254;
			rwdtbl = 61201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3332203;
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

